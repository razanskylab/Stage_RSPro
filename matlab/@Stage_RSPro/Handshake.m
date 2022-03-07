% File: Handshake.m @ Stage_RSPro
% Author: Urs Hofmann
% Mail: mail@hofmannu.org
% Date: 08.03.2022

function Handshake(r)
	answer = read(r.s, 1, "uint8");

	if (answer == 'w')
		warning("A warning occured");
	elseif (answer == 'e')
		error('An error occured');
	elseif (answer == 'r')
		% perfect
	else
		error("Stage controller did not give handshake, but: %s", ...
			string(answer));
	end
end