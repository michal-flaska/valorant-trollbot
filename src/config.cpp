else if (section == "inspectspam") {
	if (key == "enabled") cfg.inspect.enabled = val == "1";
	else if (key == "mode") cfg.inspect.mode = val;
	else if (key == "triggerkey") cfg.inspect.triggerKey = hexToUInt(val);
	else if (key == "inspectkey") cfg.inspect.inspectKey = hexToUInt(val);
	else if (key == "startdelay") cfg.inspect.startDelay = std::stoul(val);
	else if (key == "repeatdelay") cfg.inspect.repeatDelay = std::stoul(val);
}
else if (section == "mouseglitch") {
	if (key == "enabled") cfg.mouseGlitch.enabled = val == "1";
	else if (key == "mode") cfg.mouseGlitch.mode = val;
	else if (key == "triggerkey") cfg.mouseGlitch.triggerKey = hexToUInt(val);
	else if (key == "maxdistance") cfg.mouseGlitch.maxDistance = std::stoi(val);
	else if (key == "startdelay") cfg.mouseGlitch.startDelay = std::stoul(val);
	else if (key == "repeatdelay") cfg.mouseGlitch.repeatDelay = std::stoul(val);
}
