% File: Disconnect.m @ Stage_RSPro
% Author: Urs Hofmannm
% Mail: mail@hofmannu.org
% Date: 07.03.2022

function Disconnect(r)

	fprintf("[Stage_RSPro] Disconnecting stage... ");
	tStart = tic();

	if r.isConnected
		r.s = [];
		r.isConnected = 0; 
	end

	fprintf("done after %.1f sec!\n", toc(tStart));
end