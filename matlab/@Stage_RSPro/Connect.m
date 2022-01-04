function Connect(r)
	
	if (~r.isConnected)
		r.s = serialport(...
			Stage_RSPro.COM_PORT, Stage_RSPro.BAUD_RATE);
		r.isConnected = 1;
	end
end