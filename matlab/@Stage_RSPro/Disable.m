% File: Disable.m @ Stage_RSPro
% Author: Urs Hofmann
% Mail: mail@hofmannu.org
% Date: 08.03.2022

function Disable(r)

	fprintf("[Stage_RSPro] Disable motors... ");
	tStart = tic();

	write(r.s, 'o', "uint8");
	answer = read(r.s, 1, "uint8");
	if (answer ~= 'o')
		error("Could not enable motor coils");
	end

	r.Handshake();

	fprintf("done after %.2f sec!\n", toc(tStart));

end