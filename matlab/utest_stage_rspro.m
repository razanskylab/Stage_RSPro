% File: utest_stage_rspro.m
% Author: Urs Hofmann
% Mail: mail@hofmannu.org
% Date: 07.03.2022


R = Stage_RSPro();

for i =1:10
	R.Disconnect();
	R.Connect();
end

for i = 1:10
	R.Identify();
end

clear all;
