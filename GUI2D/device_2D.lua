format_version = "1.0"
Q=5

front = {
	S_backdrop = {{path="Reason_GUI_front_root_panel"}},
	{
		S_device_name = {
			offset = {337*Q,27*Q},
			{path="TapeHorz"},
		},
		S_toggle_button_prop_audio_switch = {
			offset = {120*Q,13*Q},
			{path="Reason_GUI_front_root_audio_switch_scaled_knob", frames = 2},
		},
		S_toggle_button_prop_xfade_switch = {
			offset = {295*Q,15*Q},
			{path="Reason_GUI_front_root_audio_xfade_button", frames = 2},
		},
		S_sequence_meter_prop_soundOn = {
			offset = {104*Q,9*Q},
			{path="Reason_GUI_front_root_audio_soundOnLED_lamp", frames = 2},
		},
		S_toggle_button_prop_cv_switch = {
			offset = {450*Q,13*Q},
			{path="Reason_GUI_front_root_cv_switch_scaled_knob", frames = 2},
		},
		S_value_display_prop_audio_labelA = {
			offset = {198*Q,14*Q},
			{path="81x14_5x5"},
		},
		S_sequence_meter_prop_audio_ledA = {
			offset = {186*Q,16*Q},
			{path="Reason_GUI_front_root_audio_ledA_lamp", frames = 2},
		},
		S_value_display_prop_cv_labelA = {
			offset = {528*Q,14*Q},
			{path="81x14_5x5"},
		},
		S_sequence_meter_prop_cv_ledA = {
			offset = {516*Q,16*Q},
			{path="Reason_GUI_front_root_cv_ledA_lamp", frames = 2},
		},
		S_value_display_prop_audio_labelB = {
			offset = {198*Q,41*Q},
			{path="81x14_5x5"},
		},
		S_sequence_meter_prop_audio_ledB = {
			offset = {186*Q,42*Q},
			{path="Reason_GUI_front_root_audio_ledB_lamp", frames = 2},
		},
		S_value_display_prop_cv_labelB = {
			offset = {528*Q,41*Q},
			{path="81x14_5x5"},
		},
		S_sequence_meter_prop_cv_ledB = {
			offset = {516*Q,42*Q},
			{path="Reason_GUI_front_root_cv_ledB_lamp", frames = 2},
		},
	},
}

folded_front = {
	S_backdrop = {{path="Reason_GUI_front_folded_root_panel"}},
	{
		S_device_name = {
			offset = {337*Q,8*Q},
			{path="TapeHorz"},
		},
		S_sequence_meter_prop_soundOn = {
			offset = {146*Q,9*Q},
			{path="Reason_GUI_front_folded_root_audio_soundOnLED_lamp", frames = 2},
		},
		S_toggle_button_prop_audio_switch = {
			offset = {213*Q,2*Q},
			{path="Reason_GUI_front_folded_root_audio_switch_scaled_knob", frames = 2},
		},
		S_toggle_button_prop_cv_switch = {
			offset = {543*Q,2*Q},
			{path="Reason_GUI_front_folded_root_cv_switch_scaled_knob", frames = 2},
		},
		S_sequence_meter_prop_audio_ledA = {
			offset = {172*Q,9*Q},
			{path="Reason_GUI_front_folded_root_audio_ledA_lamp", frames = 2},
		},
		S_sequence_meter_prop_cv_ledA = {
			offset = {502*Q,9*Q},
			{path="Reason_GUI_front_folded_root_cv_ledA_lamp", frames = 2},
		},
		S_sequence_meter_prop_audio_ledB = {
			offset = {267*Q,9*Q},
			{path="Reason_GUI_front_folded_root_audio_ledB_lamp", frames = 2},
		},
		S_sequence_meter_prop_cv_ledB = {
			offset = {597*Q,9*Q},
			{path="Reason_GUI_front_folded_root_cv_ledB_lamp", frames = 2},
		},
	},
}

back = {
	S_backdrop = {{path="Reason_GUI_back_root_panel"}},
	{
		S_device_name = {
			offset = {45*Q,19*Q},
			{path="TapeHorz"},
		},
		S_placeholder = {
			offset = {45*Q,34*Q},
			{path="Placeholder"},
		},
		S_audio_output_socket_audioOutputLeft = {
			offset = {282*Q,27*Q},
			{path="SharedAudioJack", frames = 3},
		},
		S_audio_output_socket_audioOutputRight = {
			offset = {313*Q,27*Q},
			{path="SharedAudioJack", frames = 3},
		},
		S_cv_input_socket_cvInAudio = {
			offset = {346*Q,28*Q},
			{path="SharedCVJack", frames = 3},
		},
		S_cv_input_socket_cvInCv = {
			offset = {628*Q,28*Q},
			{path="SharedCVJack", frames = 3},
		},
		S_cv_output_socket_cvOutput = {
			offset = {590*Q,34*Q},
			{path="SharedCVJack", frames = 3},
		},
		S_audio_input_socket_audioInputLeftA = {
			offset = {153*Q,27*Q},
			{path="SharedAudioJack", frames = 3},
		},
		S_audio_input_socket_audioInputRightA = {
			offset = {184*Q,27*Q},
			{path="SharedAudioJack", frames = 3},
		},
		S_cv_input_socket_cvInputA = {
			offset = {490*Q,34*Q},
			{path="SharedCVJack", frames = 3},
		},
		S_audio_input_socket_audioInputLeftB = {
			offset = {218*Q,27*Q},
			{path="SharedAudioJack", frames = 3},
		},
		S_audio_input_socket_audioInputRightB = {
			offset = {249*Q,27*Q},
			{path="SharedAudioJack", frames = 3},
		},
		S_cv_input_socket_cvInputB = {
			offset = {540*Q,34*Q},
			{path="SharedCVJack", frames = 3},
		},
	},
}

folded_back = {
	S_backdrop = {{path="Reason_GUI_back_folded_root_panel"}},
	S_cable_origin = {offset={1885,75}},
	{
		S_device_name = {
			offset = {594*Q,8*Q},
			{path="TapeHorz"},
		},
	},
}

