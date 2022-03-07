% File: utest_stage_rspro.m
% Author: Urs Hofmann
% Mail: mail@hofmannu.org
% Date: 07.03.2022

R = Stage_RSPro();

% check if initial position is 0
if (R.pos ~= 0)
	error('Initial position should be zero');
end

% lets define a certain pitch
R.pitch = 10;
if (R.pitch ~= 10)
	error("Pitch should now be 10 bro");
end

% lets define a certain velocity
R.vel = 10.2;
errorVel = abs(R.vel - 10.2);
if (errorVel > 1e-6)
	error("Velocity set does not seem to work");
end

R.Enable();
R.pos = 10;
if (R.pos ~= 10)
	error("Could not move to position 10");
end
R.pos = 0;

for i=1:10
	R.pos = 0;
	R.pos = i;
end
R.Disable();

% connecting and disconnecting test
for i =1:10
	R.Disconnect();
	R.Connect();
end

for i = 1:10
	R.Identify();
end

for i = 1:10
	R.Enable();
	R.Disable();
end

clear all;
