format_version = "1.0"

-- Note that remote name text lenghts are: 
--		internal_name = max 64 chars, 
--		short_name = max 8 chars, 
--		shortest_ui_name = max 4 chars

 -- english
texts = {

  -- output sockets
	["audio output main left"] = "Switched Audio Output Left",
	["audio output main right"] = "Switched Audio Output Right",
	["cv output main"] = "Switched CV Output",

  -- input sockets
  ["cv in audio switch"] = "CV In (Audio switch control)",
  ["cv in cv switch"] = "CV In (CV switch control)",
	
	["propertyname prop_audio_switch"] = "Switch Audio A & B",
	["propertyname prop_audio_switch A"] = "Audio A on",
	["propertyname prop_audio_switch B"] = "Audio B on",

	["propertyname prop_xfade_switch"] = "Soften",
	["propertyname prop_xfade_switch on"] = "Soften on",
	["propertyname prop_xfade_switch off"] = "Soften off",

	["propertyname prop_soundOn"] = "Sound On",

	["propertyname prop_cv_switch"] = "Switch CV A & B",
	["propertyname prop_cv_switch A"] = "CV A on",
	["propertyname prop_cv_switch B"] = "CV B on",

  ["short property name remote prop_audio_switch"] = "ABAuSw",
  ["shortest property name remote prop_audio_switch"] = "ABAS",

  ["short property name remote prop_xfade_switch"] = "ABAuXFSw",
  ["shortest property name remote prop_xfade_switch"] = "AuXF",

  ["short property name remote prop_cv_switch"] = "ABCVSw",
  ["shortest property name remote prop_cv_switch"] = "ABCS",

}

for k, input in pairs({'A', 'B'}) do
	texts["audioInputLeft" .. input] = "Audio [" .. input .. "] Input Left"
	texts["audioInputRight" .. input] = "Audio [" .. input .. "] Input Right"
	texts["cvInput" .. input] = "CV [" .. input .. "] Input"
	texts["propertyname prop_audio_led" .. input] = "Audio [" .. input .. "] On/Off"
	texts["propertyname prop_cv_led" .. input] = "CV [" .. input .. "] On/Off"
end
