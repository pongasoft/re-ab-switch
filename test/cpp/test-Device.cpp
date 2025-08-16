#include <gtest/gtest.h>
#include <Device.h>
#include <re/mock/DeviceTesters.h>
#include <re_cmake_build.h>

using namespace re::mock;

/**
 * Represents the state of the device from an external point of view */
struct State
{
  static constexpr bool A = false;
  static constexpr bool B = true;

  bool soundOn{false};
  bool audioLEDA{false};
  bool cvLEDA{false};
  bool audioLEDB{false};
  bool cvLEDB{false};
  bool audioSwitch{A};
  bool cvSwitch{A};
  bool xFade{false};

  bool operator==(State const &rhs) const;

  bool operator!=(State const &rhs) const;

  std::string to_string() const
  {
    return fmt::printf("soundOn=%d, audioLEDA=%d, cvLEDA=%d, audioLEDB=%d, cvLEDB=%d, audioSwitch=%d, cvSwitch=%d, xFade=%d",
                       soundOn, audioLEDA, cvLEDA, audioLEDB, cvLEDB, audioSwitch, cvSwitch, xFade);
  }

  // Create a free inline friend function.
  friend std::ostream& operator<<(std::ostream& os, const State& s) {
    return os << s.to_string();  // whatever needed to print bar to os
  }

  static State from(HelperTester<Device> &iTester)
  {
    auto re = iTester.device();
    
    return {
      .soundOn = re.getBool("/custom_properties/prop_soundOn"),
      .audioLEDA = re.getBool("/custom_properties/prop_audio_ledA"),
      .cvLEDA = re.getBool("/custom_properties/prop_cv_ledA"),
      .audioLEDB = re.getBool("/custom_properties/prop_audio_ledB"),
      .cvLEDB = re.getBool("/custom_properties/prop_cv_ledB"),
      .audioSwitch = re.getBool("/custom_properties/prop_audio_switch"),
      .cvSwitch = re.getBool("/custom_properties/prop_cv_switch"),
      .xFade = re.getBool("/custom_properties/prop_xfade_switch")
    };
  }
};

bool State::operator==(State const &rhs) const
{
  return soundOn == rhs.soundOn &&
         audioLEDA == rhs.audioLEDA &&
         cvLEDA == rhs.cvLEDA &&
         audioLEDB == rhs.audioLEDB &&
         cvLEDB == rhs.cvLEDB &&
         audioSwitch == rhs.audioSwitch &&
         cvSwitch == rhs.cvSwitch &&
         xFade == rhs.xFade;
}

bool State::operator!=(State const &rhs) const
{
  return !(rhs == *this);
}

MockAudioDevice::buffer_type xfade(MockAudioDevice::buffer_type const &iFromBuffer,
                                   MockAudioDevice::buffer_type const &iToBuffer)
{
  MockAudioDevice::buffer_type res{};
  for(int i = 0; i < Rack::kNumSamplesPerBatch; i++)
  {
    double f = static_cast<double>(i) / (Rack::kNumSamplesPerBatch - 1.0);
    res[i] = (iToBuffer[i] * f) + (iFromBuffer[i] * (1.0 - f));
  }
  return res;
}

MockAudioDevice::StereoBuffer xfade(MockAudioDevice::StereoBuffer const &iFromBuffer,
                                   MockAudioDevice::StereoBuffer const &iToBuffer)
{
  return { .fLeft = xfade(iFromBuffer.fLeft, iToBuffer.fLeft), .fRight = xfade(iFromBuffer.fRight, iToBuffer.fRight) };
}

// Device - SampleRate
TEST(Device, SampleRate)
{
  auto c = DeviceConfig<Device>::fromJBoxExport(RE_CMAKE_PROJECT_DIR);
  auto tester = HelperTester<Device>(c);

  ASSERT_EQ(44100, tester.device()->getSampleRate());

  State s{};
  ASSERT_EQ(s, State::from(tester));
}

// Device - AudioSwitch
TEST(Device, AudioSwitch)
{
  auto c = DeviceConfig<Device>::fromJBoxExport(RE_CMAKE_PROJECT_DIR);
  auto tester = HelperTester<Device>(c);

  auto srcA = tester.wireNewAudioSrc();
  auto srcB = tester.wireNewAudioSrc();
  auto dst = tester.wireNewAudioDst("audioOutputLeft", "audioOutputRight");
  auto srcCV = tester.wireNewCVSrc();

  State s{};

  ASSERT_EQ(s, State::from(tester));

  /*******************************/////////////******************************/
  /*                             < FIRST FRAME >                            */
  /*******************************/////////////******************************/
  tester.nextBatch();

  ////////// Checks //////////

  // after the first frame, the switch is now in its default state where A is selected for audio and cv (set by RT)
  // no input connected => audio should stay at 0
  s.audioLEDA = true;
  s.cvLEDA = true;
  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(0, 0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - wiring srcA -> abSwitch, srcB -> abSwitch //////////

  tester.wire(srcA, "audioInputLeftA", "audioInputRightA");
  tester.wire(srcB, "audioInputLeftB", "audioInputRightB");

  tester.nextBatch();

  ////////// Checks - input is still 0/0 //////////

  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(0, 0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - setting A to 1/2 and B to 3/4 //////////

  srcA->fBuffer.fill(1.0, 2.0);
  srcB->fBuffer.fill(3.0, 4.0);

  tester.nextBatch();

  ////////// Checks //////////

  // since A is selected, we should get 1/2
  s.soundOn = true; // not 0 => soundOn is true
  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(1.0, 2.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch to B //////////

  s.audioSwitch = State::B;
  tester.device().setBool("/custom_properties/prop_audio_switch", s.audioSwitch);

  tester.nextBatch();

  ////////// Checks - srcB should now be the output //////////

  // led lights switched
  s.audioLEDA = false;
  s.audioLEDB = true;

  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - turn on xfade //////////

  s.xFade = true;
  tester.device().setBool("/custom_properties/prop_xfade_switch", s.xFade);

  tester.nextBatch();

  ////////// Checks - same output (xfade only applies on switching) //////////

  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch to A //////////

  s.audioSwitch = State::A;
  tester.device().setBool("/custom_properties/prop_audio_switch", s.audioSwitch);

  tester.nextBatch();

  ////////// Checks - srcA should now be the output but it should cross fade //////////

  // led lights switched
  s.audioLEDA = true;
  s.audioLEDB = false;

  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, xfade(MockAudioDevice::buffer(3.0, 4.0), MockAudioDevice::buffer(1.0, 2.0)));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - disable xfade and wire cv (set to 0 = B) //////////
  // From documentation: Any positive (or 0) CV value will trigger the B input and any
  // negative CV value will trigger the A input.

  s.xFade = false;
  tester.device().setBool("/custom_properties/prop_xfade_switch", s.xFade);
  tester.wire(srcCV, "cvInAudio");
  srcCV->fValue = 0;

  tester.nextBatch();

  ////////// Checks - srcB should now be the output //////////

  // led lights switched
  s.audioLEDA = false;
  s.audioLEDB = true;
  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch to B //////////

  s.audioSwitch = State::B;
  tester.device().setBool("/custom_properties/prop_audio_switch", s.audioSwitch);

  tester.nextBatch();

  ////////// Checks - srcB remains the output //////////

  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch to A //////////

  s.audioSwitch = State::A;
  tester.device().setBool("/custom_properties/prop_audio_switch", s.audioSwitch);

  tester.nextBatch();

  ////////// Checks - srcB remains the output (CV override) //////////

  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch CV to negative (A) //////////

  srcCV->fValue = -1.0;

  tester.nextBatch();

  ////////// Checks - srcA is now the output //////////

  // led lights switched
  s.audioLEDA = true;
  s.audioLEDB = false;
  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(1.0, 2.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch CV to positive (B) //////////

  srcCV->fValue = 1.0;

  tester.nextBatch();

  ////////// Checks - srcB is now the output //////////

  // led lights switched
  s.audioLEDA = false;
  s.audioLEDB = true;
  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we disconnect CV //////////

  tester.unwire(srcCV);

  tester.nextBatch();

  ////////// Checks - srcA is now the output //////////

  // led lights switched
  s.audioLEDA = true;
  s.audioLEDB = false;
  ASSERT_EQ(s, State::from(tester));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(1.0, 2.0));


}
