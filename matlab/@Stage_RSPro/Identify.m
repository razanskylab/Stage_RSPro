% File: Identify.m @ Stage_RSPro
% Author: Urs Hofmann
% Mail: mail@hofmannu.org
% Date: 04.01.2022

function Identify(r)

	fprintf("[Stage_RSPro] Identifying device... ");
	tStart = tic();

	write(r.s, 'i', "uint8");
	r.Handshake();

	fprintf("done after %.2f sec!\n", toc(tStart));

end