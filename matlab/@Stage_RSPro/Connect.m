% File: Connect.m @ Stage_RSPro
% Author: Urs Hofmann
% Mail: mail@hofmannu.org
% Date: 07.03.2022

function Connect(r)
		
	fprintf("[Stage_RSPro] Connecting to port %s... ", r.COM_PORT);
	tStart = tic();

	if (~r.isConnected)
		r.s = serialport(r.COM_PORT, r.BAUD_RATE);
		r.isConnected = 1;
	end

	fprintf("done after %.1f sec!\n", toc(tStart));
end