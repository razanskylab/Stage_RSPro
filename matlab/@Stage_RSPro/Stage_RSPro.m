% File: Stage_RSPro.m @ Stage_RSPro
% Author: Urs Hofmann
% Mail: mail@hofmannu.org
% Date: 04.01.2022

% Description: A simple MATLAB wrapper class to interface a stepper
% motor based stage

classdef Stage_RSPro < handle

	properties(Constant)
		COM_PORT(1, :) char = 'COM3';
		BAUD_RATE(1, 1) = 9600;
	end

	properties(SetAccess = private)
		s; % serial port object
		isConnected(1, 1) logical = 0;
	end

	properties (Dependent)
		pos(1, 1) single; % position of the stage
		vel(1, 1) single; % moving velocity in mm/s
		pitch(1, 1) single;
		stepsPerRev(1, 1) single;
	end

	methods

		% class constructor and destructor
		function obj = Stage_RSPro()
			obj.Connect();
		end
		
		function delete(obj)
			obj.Disconnect();
		end

		% get and set function for position
		function pos = get.pos(r)
			write(r.s, 'p', "uint8");
			pos = read(r.s, 1, 'single');
			r.Handshake();
		end

		function set.pos(r, pos)
			write(r.s, 'a', "uint8");
			write(r.s, single(pos), 'single');
			r.Handshake();
		end

		% get and set function for velocity
		function vel = get.vel(r)
			write(r.s, 'w', "uint8");
			vel = read(r.s, 1, 'single');
			r.Handshake();
		end

		function set.vel(r, vel)
			write(r.s, 'v', "uint8");
			write(r.s, single(vel), 'single');
			r.Handshake();
		end

		% get and set function for lead screw pitch
		function pitch = get.pitch(r)
			write(r.s, 't', "uint8");
			pitch = read(r.s, 1, 'single');
			r.Handshake();
		end

		function set.pitch(r, pitch)
			write(r.s, 'y', "uint8");
			write(r.s, single(pitch), 'single');
			r.Handshake();
		end

		% get and set function for steps per revolution
		function stepsPerRev = get.stepsPerRev(r)
			write(r.s, 's', "uint8");
			stepsPerRev = read(r.s, 1, 'single');
			r.Handshake();
		end

		function set.stepsPerRev(r, stepsPerRev)
			write(r.s, 'd', "uint8");
			write(r.s, single(stepsPerRev), 'single');
			r.Handshake();
		end

		% implemented stuff
  	Identify(r);
  	Connect(r);
  	Disconnect(r);
  	Handshake(r);
  	Enable(r);
  	Disable(r);

  	% not implemented yet
  	Home(r);
  	Move_NoWait(r);
  	Wait_Move(r);
	end

end