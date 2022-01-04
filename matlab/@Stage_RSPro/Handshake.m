% File: Handshake.m @ Stage_RSPro
% Author: Urs Hofmann
% Mail: mail@hofmannu.org


function Handshake(r)
	answer = char(readline(r.s));
	if ~(answer(1:end-1) == 'r')
		error("Stage controller did not give handshake");
	end
end