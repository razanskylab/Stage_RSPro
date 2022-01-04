% File: Identify.m @ Stage_RSPro
% Author: Urs Hofmann
% Mail: mail@hofmannu.org
% Date: 04.01.2022

function Identify(r)

	write(r.s, 'i', "uint8");
	r.Handshake();

end