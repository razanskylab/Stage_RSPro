% File: Enable.m @ Stage_RSPro
% Author: Urs Hofmann
% Mail: mail@hofmannu.org
% Date: 08.03.2022

function Enable(r)

	fprintf("[Stage_RSPro] Enable motors... ");
	tStart = tic();

	write(r.s, 'e', "uint8");
	answer = read(r.s, 1, "uint8");
	if (answer ~= 'e')
		error("Could not enable motor coils");
	end

	r.Handshake();

	fprintf("done after %.2f sec!\n", toc(tStart));

end