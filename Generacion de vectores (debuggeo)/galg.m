
x =[1 2 3 4 78 88 96 74 55 55];

k=1;
% Geortzel Algorithm

% [ Xk, Ak] = galg(x,k)

% x = input vetcor; k = frequency index

% Xk = kth DFT coeficient; Ak = magnitude of the kth DFT coefficient

N = length(x); x =[x 0];

vk = zeros(1,N + 3);

for n = 1:N + 1

 vk(n + 2)=2*cos(2*pi*k/N)*vk(n + 1)-vk(n)+x(n);

end

Xk = vk(N + 3)-exp(-2*pi*j*k/N)*vk(N + 2);

Ak = vk(N + 3)*vk(N + 3)+vk(N + 2)*vk(N + 2)-2*cos(2*pi*k/N)*vk(N + 3)*vk(N + 2);

Ak = sqrt(Ak)/N;

