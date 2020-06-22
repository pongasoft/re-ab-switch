format_version = "2.0"
Q=5

front = jbox.panel{
	graphics = { node = "S_backdrop" },
	widgets = {
		jbox.device_name{
			graphics = { node = "S_device_name" },
		},
		jbox.toggle_button{
			graphics = { node = "S_toggle_button_prop_audio_switch", hit_boundaries = { left=Q*0, top=Q*0, right=Q*0, bottom=Q*5 } },
			value = "/custom_properties/prop_audio_switch",
		},
		jbox.toggle_button{
			graphics = { node = "S_toggle_button_prop_xfade_switch" },
			value = "/custom_properties/prop_xfade_switch",
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_soundOn" },
			value = "/custom_properties/prop_soundOn",
		},
		jbox.toggle_button{
			graphics = { node = "S_toggle_button_prop_cv_switch", hit_boundaries = { left=Q*0, top=Q*0, right=Q*0, bottom=Q*5 } },
			value = "/custom_properties/prop_cv_switch",
		},
		jbox.value_display{
			graphics = { node = "S_value_display_prop_audio_labelA" },
			text_style = "Small LCD font",
			show_automation_rect = false,
			value = "/custom_properties/prop_audio_labelA",
			text_color = { 20, 20, 20 },
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_audio_ledA" },
			value = "/custom_properties/prop_audio_ledA",
		},
		jbox.value_display{
			graphics = { node = "S_value_display_prop_cv_labelA" },
			text_style = "Small LCD font",
			show_automation_rect = false,
			value = "/custom_properties/prop_cv_labelA",
			text_color = { 20, 20, 20 },
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_cv_ledA" },
			value = "/custom_properties/prop_cv_ledA",
		},
		jbox.value_display{
			graphics = { node = "S_value_display_prop_audio_labelB" },
			text_style = "Small LCD font",
			show_automation_rect = false,
			value = "/custom_properties/prop_audio_labelB",
			text_color = { 20, 20, 20 },
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_audio_ledB" },
			value = "/custom_properties/prop_audio_ledB",
		},
		jbox.value_display{
			graphics = { node = "S_value_display_prop_cv_labelB" },
			text_style = "Small LCD font",
			show_automation_rect = false,
			value = "/custom_properties/prop_cv_labelB",
			text_color = { 20, 20, 20 },
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_cv_ledB" },
			value = "/custom_properties/prop_cv_ledB",
		},
	},
}

folded_front = jbox.panel{
	graphics = { node = "S_backdrop" },
	widgets = {
		jbox.device_name{
			graphics = { node = "S_device_name" },
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_soundOn" },
			value = "/custom_properties/prop_soundOn",
		},
		jbox.toggle_button{
			graphics = { node = "S_toggle_button_prop_audio_switch" },
			value = "/custom_properties/prop_audio_switch",
		},
		jbox.toggle_button{
			graphics = { node = "S_toggle_button_prop_cv_switch" },
			value = "/custom_properties/prop_cv_switch",
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_audio_ledA" },
			value = "/custom_properties/prop_audio_ledA",
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_cv_ledA" },
			value = "/custom_properties/prop_cv_ledA",
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_audio_ledB" },
			value = "/custom_properties/prop_audio_ledB",
		},
		jbox.sequence_meter{
			graphics = { node = "S_sequence_meter_prop_cv_ledB" },
			value = "/custom_properties/prop_cv_ledB",
		},
	},
}

back = jbox.panel{
	graphics = { node = "S_backdrop" },
	widgets = {
		jbox.device_name{
			graphics = { node = "S_device_name" },
		},
		jbox.placeholder{
			graphics = { node = "S_placeholder" },
		},
		jbox.audio_output_socket{
			graphics = { node = "S_audio_output_socket_audioOutputLeft" },
			socket = "/audio_outputs/audioOutputLeft",
		},
		jbox.audio_output_socket{
			graphics = { node = "S_audio_output_socket_audioOutputRight" },
			socket = "/audio_outputs/audioOutputRight",
		},
		jbox.cv_input_socket{
			graphics = { node = "S_cv_input_socket_cvInAudio" },
			socket = "/cv_inputs/cvInAudio",
		},
		jbox.cv_input_socket{
			graphics = { node = "S_cv_input_socket_cvInCv" },
			socket = "/cv_inputs/cvInCv",
		},
		jbox.cv_output_socket{
			graphics = { node = "S_cv_output_socket_cvOutput" },
			socket = "/cv_outputs/cvOutput",
		},
		jbox.audio_input_socket{
			graphics = { node = "S_audio_input_socket_audioInputLeftA" },
			socket = "/audio_inputs/audioInputLeftA",
		},
		jbox.audio_input_socket{
			graphics = { node = "S_audio_input_socket_audioInputRightA" },
			socket = "/audio_inputs/audioInputRightA",
		},
		jbox.cv_input_socket{
			graphics = { node = "S_cv_input_socket_cvInputA" },
			socket = "/cv_inputs/cvInputA",
		},
		jbox.audio_input_socket{
			graphics = { node = "S_audio_input_socket_audioInputLeftB" },
			socket = "/audio_inputs/audioInputLeftB",
		},
		jbox.audio_input_socket{
			graphics = { node = "S_audio_input_socket_audioInputRightB" },
			socket = "/audio_inputs/audioInputRightB",
		},
		jbox.cv_input_socket{
			graphics = { node = "S_cv_input_socket_cvInputB" },
			socket = "/cv_inputs/cvInputB",
		},
	},
}

folded_back = jbox.panel{
	graphics = { node = "S_backdrop" },
	cable_origin = { node = "S_cable_origin" },
	widgets = {
		jbox.device_name{
			graphics = { node = "S_device_name" },
		},
	},
}

