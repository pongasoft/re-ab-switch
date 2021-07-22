#include <gtest/gtest.h>
#include <Device.h>
#include <re/mock/Rack.h>
#include <re/mock/MockDevices.h>

using namespace re::mock;

auto newABSwitch(Rack &iRack) {
  Config c = Config::byDefault<Device>([](LuaJbox &jbox, MotherboardDef &def, RealtimeController &rtc, Realtime &rt) {
    std::array<char const *, 2> inputs{"A", "B"};

    // motherboard_def.lua
    def.rt_owner.properties["prop_soundOn"] = jbox.boolean(false);

    for(auto input: inputs) {
      def.audio_inputs[fmt::printf("audioInputLeft%s", input)] = jbox.audio_input();
      def.audio_inputs[fmt::printf("audioInputRight%s", input)] = jbox.audio_input();
      def.cv_inputs[fmt::printf("cvInput%s", input)] = jbox.cv_input();
      def.rt_owner.properties[fmt::printf("prop_audio_led%s", input)] = jbox.boolean(false);
      def.rt_owner.properties[fmt::printf("prop_cv_led%s", input)] = jbox.boolean(false);
    }

    def.cv_inputs["cvInAudio"] = jbox.cv_input();
    def.cv_inputs["cvInCv"] = jbox.cv_input();
    def.cv_outputs["cvOutput"] = jbox.cv_output();

    def.audio_outputs["audioOutputLeft"] = jbox.audio_output();
    def.audio_outputs["audioOutputRight"] = jbox.audio_output();

    def.document_owner.properties["prop_audio_switch"] = jbox.boolean({.property_tag = 100, .default_value = false});
    def.document_owner.properties["prop_xfade_switch"] = jbox.boolean({.property_tag = 101, .default_value = false});
    def.document_owner.properties["prop_cv_switch"] = jbox.boolean({.property_tag = 200, .default_value = false});

    // realtime_controller.lua
    rtc.rt_input_setup.notify = {
      "/cv_inputs/cvInAudio/connected",
      "/cv_inputs/cvInAudio/value",
      "/cv_inputs/cvInCv/connected",
      "/cv_inputs/cvInCv/value",
      "/cv_inputs/cvInputA/connected",
      "/cv_inputs/cvInputA/value",
      "/cv_inputs/cvInputB/connected",
      "/cv_inputs/cvInputB/value",

      "/cv_outputs/cvOutput/connected",

      "/audio_inputs/audioInputLeftA/connected",
      "/audio_inputs/audioInputRightA/connected",
      "/audio_inputs/audioInputLeftB/connected",
      "/audio_inputs/audioInputRightB/connected",

      "/audio_outputs/audioOutputLeft/connected",
      "/audio_outputs/audioOutputRight/connected",

      "/custom_properties/prop_audio_switch",
      "/custom_properties/prop_cv_switch",
      "/custom_properties/prop_xfade_switch",
    };

    // rt
    rt.create_native_object = JBox_Export_CreateNativeObject; // use actual function for test
    rt.render_realtime = JBox_Export_RenderRealtime;          // use actual function for test
  });

  return iRack.newDevice<Device>(c);
}

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

  static State from(Rack::ExtensionDevice<Device> &re)
  {
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
  for(int i = 0; i < MockAudioDevice::NUM_SAMPLES_PER_FRAME; i++)
  {
    double f = static_cast<double>(i) / (MockAudioDevice::NUM_SAMPLES_PER_FRAME - 1.0);
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
  Rack rack{};

  // this tests the creation of the device
  auto abSwitch = newABSwitch(rack);

  ASSERT_EQ(44100, abSwitch->getSampleRate());

  State s{};
  ASSERT_EQ(s, State::from(abSwitch));
}

// Device - AudioSwitch
TEST(Device, AudioSwitch)
{
  Rack rack{};

  auto abSwitch = newABSwitch(rack);

  auto srcA = rack.newDevice<MAUSrc>(MAUSrc::Config);
  auto srcB = rack.newDevice<MAUSrc>(MAUSrc::Config);
  auto dst = rack.newDevice<MAUDst>(MAUDst::Config);
  auto srcCV = rack.newDevice<MCVSrc>(MCVSrc::Config);

  MockAudioDevice::wire(rack, abSwitch.getStereoAudioOutSocket("audioOutputLeft", "audioOutputRight"), dst);

  State s{};

  ASSERT_EQ(s, State::from(abSwitch));

  /*******************************/////////////******************************/
  /*                             < FIRST FRAME >                            */
  /*******************************/////////////******************************/
  rack.nextFrame();

  ////////// Checks //////////

  // after the first frame, the switch is now in its default state where A is selected for audio and cv (set by RT)
  // no input connected => audio should stay at 0
  s.audioLEDA = true;
  s.cvLEDA = true;
  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(0, 0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - wiring srcA -> abSwitch, srcB -> abSwitch //////////

  MockAudioDevice::wire(rack, srcA, abSwitch.getStereoAudioInSocket("audioInputLeftA", "audioInputRightA"));
  MockAudioDevice::wire(rack, srcB, abSwitch.getStereoAudioInSocket("audioInputLeftB", "audioInputRightB"));

  rack.nextFrame();

  ////////// Checks - input is still 0/0 //////////

  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(0, 0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - setting A to 1/2 and B to 3/4 //////////

  srcA->fBuffer.fill(1.0, 2.0);
  srcB->fBuffer.fill(3.0, 4.0);

  rack.nextFrame();

  ////////// Checks //////////

  // since A is selected, we should get 1/2
  s.soundOn = true; // not 0 => soundOn is true
  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(1.0, 2.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch to B //////////

  s.audioSwitch = State::B;
  abSwitch.setBool("/custom_properties/prop_audio_switch", s.audioSwitch);

  rack.nextFrame();

  ////////// Checks - srcB should now be the output //////////

  // led lights switched
  s.audioLEDA = false;
  s.audioLEDB = true;

  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - turn on xfade //////////

  s.xFade = true;
  abSwitch.setBool("/custom_properties/prop_xfade_switch", s.xFade);

  rack.nextFrame();

  ////////// Checks - same output (xfade only applies on switching) //////////

  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch to A //////////

  s.audioSwitch = State::A;
  abSwitch.setBool("/custom_properties/prop_audio_switch", s.audioSwitch);

  rack.nextFrame();

  ////////// Checks - srcA should now be the output but it should cross fade //////////

  // led lights switched
  s.audioLEDA = true;
  s.audioLEDB = false;

  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, xfade(MockAudioDevice::buffer(3.0, 4.0), MockAudioDevice::buffer(1.0, 2.0)));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - disable xfade and wire cv (set to 0 = B) //////////
  // From documentation: Any positive (or 0) CV value will trigger the B input and any
  // negative CV value will trigger the A input.

  s.xFade = false;
  abSwitch.setBool("/custom_properties/prop_xfade_switch", s.xFade);
  MockCVDevice::wire(rack, srcCV, abSwitch.getCVInSocket("cvInAudio"));
  srcCV->fValue = 0;

  rack.nextFrame();

  ////////// Checks - srcB should now be the output //////////

  // led lights switched
  s.audioLEDA = false;
  s.audioLEDB = true;
  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch to B //////////

  s.audioSwitch = State::B;
  abSwitch.setBool("/custom_properties/prop_audio_switch", s.audioSwitch);

  rack.nextFrame();

  ////////// Checks - srcB remains the output //////////

  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch to A //////////

  s.audioSwitch = State::A;
  abSwitch.setBool("/custom_properties/prop_audio_switch", s.audioSwitch);

  rack.nextFrame();

  ////////// Checks - srcB remains the output (CV override) //////////

  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch CV to negative (A) //////////

  srcCV->fValue = -1.0;

  rack.nextFrame();

  ////////// Checks - srcA is now the output //////////

  // led lights switched
  s.audioLEDA = true;
  s.audioLEDB = false;
  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(1.0, 2.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we switch CV to positive (B) //////////

  srcCV->fValue = 1.0;

  rack.nextFrame();

  ////////// Checks - srcB is now the output //////////

  // led lights switched
  s.audioLEDA = false;
  s.audioLEDB = true;
  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(3.0, 4.0));

  /*******************************////////////*******************************/
  /*                             < NEXT FRAME >                             */
  /*******************************////////////*******************************/
  ////////// Action - we disconnect CV //////////

  rack.unwire(srcCV.getCVOutSocket(MCVSrc::SOCKET));

  rack.nextFrame();

  ////////// Checks - srcA is now the output //////////

  // led lights switched
  s.audioLEDA = true;
  s.audioLEDB = false;
  ASSERT_EQ(s, State::from(abSwitch));
  ASSERT_EQ(dst->fBuffer, MockAudioDevice::buffer(1.0, 2.0));


}
