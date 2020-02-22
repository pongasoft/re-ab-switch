format_version = "1.0"

local rtcOwnerProperties = {
  instance = jbox.native_object {},
}

local guiOwnerProperties = {
}

local rtOwnerProperties = {
  prop_soundOn = jbox.boolean {
    default = false,
    ui_name = jbox.ui_text("propertyname prop_soundOn"),
    ui_type = jbox.ui_linear({ min = 0, max = 1, units = { { decimals = 0 } } }),
  },
}

--[[ 
Inputs/Outputs
--]]
local inputs = { 'A', 'B' }

audio_inputs = {}

cv_inputs = {}

for k, input in pairs(inputs) do
  -- defines the audio socket (left)
  local leftSocket = "audioInputLeft" .. input
  audio_inputs[leftSocket] = jbox.audio_input {
    ui_name = jbox.ui_text(leftSocket)
  }
  -- defines the audio socket (right)
  local rightSocket = "audioInputRight" .. input
  audio_inputs[rightSocket] = jbox.audio_input {
    ui_name = jbox.ui_text(rightSocket)
  }
  -- it is a stereo pair => should be auto routed
  jbox.add_stereo_audio_routing_pair {
    left = "/audio_inputs/" .. leftSocket,
    right = "/audio_inputs/" .. rightSocket
  }
  
  -- defines the cv socket
  cv_inputs["cvInput" .. input] = jbox.cv_input {
    ui_name = jbox.ui_text("cvInput" .. input)
  }
  
  guiOwnerProperties["prop_audio_label" .. input] = jbox.string {
    persistence = "patch",
  }

  guiOwnerProperties["prop_cv_label" .. input] = jbox.string {
    persistence = "patch",
  }

  -- led light (audio)
  rtOwnerProperties["prop_audio_led" .. input] = jbox.boolean {
    default = false,
    ui_name = jbox.ui_text("propertyname prop_audio_led" .. input),
    ui_type = jbox.ui_linear({ min = 0, max = 1, units = { { decimals = 0 } } }),
  }

  -- led light (cv)
  rtOwnerProperties["prop_cv_led" .. input] = jbox.boolean {
    default = false,
    ui_name = jbox.ui_text("propertyname prop_cv_led" .. input),
    ui_type = jbox.ui_linear({ min = 0, max = 1, units = { { decimals = 0 } } }),
  }
end

-- new cv inputs in 1.1: need to be declared after
-- control the audio switch via cv input
cv_inputs["cvInAudio"] = jbox.cv_input {
  ui_name = jbox.ui_text("cv in audio switch")
}
-- control the cv switch via cv input
cv_inputs["cvInCv"] = jbox.cv_input {
  ui_name = jbox.ui_text("cv in cv switch")
}


audio_outputs = {
  audioOutputLeft = jbox.audio_output {
    ui_name = jbox.ui_text("audio output main left")
  },
  audioOutputRight = jbox.audio_output {
    ui_name = jbox.ui_text("audio output main right")
  }
}

cv_outputs = {
  cvOutput = jbox.cv_output {
    ui_name = jbox.ui_text("cv output main")
  }
}

-- defines routing pairs for stereo (Reason will wire left and right automatically)

jbox.add_stereo_audio_routing_pair {
  left = "/audio_outputs/audioOutputLeft",
  right = "/audio_outputs/audioOutputRight"
}

--[[ 
Custom properties
--]]
custom_properties = jbox.property_set {
  gui_owner = {
    properties = guiOwnerProperties
  },

  document_owner = {
    properties = {
      -- the toggle switch between A (false) and B (true) (for audio)
      prop_audio_switch = jbox.boolean {
        property_tag = 100,
        default = false,
        ui_name = jbox.ui_text("propertyname prop_audio_switch"),
        ui_type = jbox.ui_selector {
          jbox.ui_text("propertyname prop_audio_switch A"),
          jbox.ui_text("propertyname prop_audio_switch B")
        },
      },
      
      -- the cross fade switch (for audio)
      prop_xfade_switch = jbox.boolean {
        property_tag = 101,
        default = false,
        ui_name = jbox.ui_text("propertyname prop_xfade_switch"),
        ui_type = jbox.ui_selector {
          jbox.ui_text("propertyname prop_xfade_switch on"),
          jbox.ui_text("propertyname prop_xfade_switch off")
        },
      },      
      -- the toggle switch between A (false) and B (true) (for cv)
      prop_cv_switch = jbox.boolean {
        property_tag = 200,
        default = false,
        ui_name = jbox.ui_text("propertyname prop_cv_switch"),
        ui_type = jbox.ui_selector {
          jbox.ui_text("propertyname prop_cv_switch A"),
          jbox.ui_text("propertyname prop_cv_switch B")
        },
      },
    }
  },
  rtc_owner = {
    properties = rtcOwnerProperties
  },
  rt_owner = {
    properties = rtOwnerProperties
  }
}

-- allow for automation
midi_implementation_chart = {
  midi_cc_chart = {
    [12] = "/custom_properties/prop_audio_switch",
    [13] = "/custom_properties/prop_cv_switch",
    [14] = "/custom_properties/prop_xfade_switch",
  }
}

remote_implementation_chart = {
  ["/custom_properties/prop_audio_switch"] = {
    internal_name = "A/B Audio Switch",
    short_ui_name = jbox.ui_text("short property name remote prop_audio_switch"),
    shortest_ui_name = jbox.ui_text("shortest property name remote prop_audio_switch")
  },
  ["/custom_properties/prop_xfade_switch"] = {
    internal_name = "Soften",
    short_ui_name = jbox.ui_text("short property name remote prop_xfade_switch"),
    shortest_ui_name = jbox.ui_text("shortest property name remote prop_xfade_switch")
  },
  ["/custom_properties/prop_cv_switch"] = {
    internal_name = "A/B CV Switch",
    short_ui_name = jbox.ui_text("short property name remote prop_cv_switch"),
    shortest_ui_name = jbox.ui_text("shortest property name remote prop_cv_switch")
  },
}

