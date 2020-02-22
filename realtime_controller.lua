format_version = "1.0"

rtc_bindings = {
  -- this will initialize the C++ object
  { source = "/environment/instance_id", dest = "/global_rtc/init_instance" },
}

global_rtc = {
  init_instance = function(source_property_path, instance_id)
    local new_no = jbox.make_native_object_rw("Instance", { instance_id })
    jbox.store_property("/custom_properties/instance", new_no);
  end,
}

rt_input_setup = {
  notify = {
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
  }
}

-- required entry => supporting everything
sample_rate_setup = {
  native = {
    22050,
    44100,
    48000,
    88200,
    96000,
    192000
  },
}
