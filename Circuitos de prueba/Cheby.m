biquad = design(fdesign.lowpass('N,F3db,Ap',11,1e3*2/44100,5),'cheby1','FilterStructure','df1sos','SystemObject',true);
fvt = fvtool(biquad,'Legend','on');
fvt.SosviewSettings.View = 'Cumulative';

sosMatrix = biquad.SOSMatrix;
sclValues = biquad.ScaleValues;
sosMatrix_q31 = fi(sosMatrix,1,32,31);
fvt_comp = fvtool(sosMatrix,sosMatrix_q31);
legend(fvt_comp,'Floating-point (double) SOS','Fixed-point (32-bit) SOS');
b = repmat(sclValues(1:(end-1)),1,3) .* sosMatrix(:,(1:3));
a = sosMatrix(:,(5:6));
num = b'; % matrix of scaled numerator sections
den = a'; % matrix of denominator sections