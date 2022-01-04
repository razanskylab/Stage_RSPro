function Disconnect(r)
	if r.isConnected
		r.s = [];
		r.isConnected = 0; 
	end
end