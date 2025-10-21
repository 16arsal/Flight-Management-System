%% Lab 1

x = 5;  % any initial guess
for n = 1:6
    x = x/2;
    fprintf('n=%d, x=%.6f\n', n, x);
end

x = 0.5;   % any nonzero start
for n = 1:6
    x = 2*x;
    fprintf('n=%d, x=%.6f\n', n, x);
end


%% Lab 2

function root = bisection(f,a,b,tol,maxiter)
    
    
    if f(a)*f(b)>0
        error('must have opposite signs');
    end

    for k = 1:maxiter
        c=(a+b) /2;

        if abs(f(c))<tol || (b-a) /2 < tol
           root = c;
           
           return
        end

        if f(a)*f(c) < 0
            
            b=c;

        else

            a=c;
            
        end
        
    end

    root = (a+b) /2
end

f = @(x) exp(-x) - x ;
a = 0;
b = 1;
tol = 1e-6;
max_iter = 100;

% Find the root
my_root = bisection(f, a, b, tol, max_iter);

fprintf('Root %.6f',my_root);

%% lab 3

% Fixed Point Iteration Method to Find Roots
g = input('Enter your function: ');
x0 = input('Enter initial guess value: ');
e = input('Tolerance value: ');
n = input('Number of iterations: ');

for i = 1:n
    x1 = g(x0);        % Compute new value using g(x)
    
    fprintf('x %d= %0.4f\n', i, x1);

    if abs(x1 - x0) < e
        break;
    end
    x0 = x1;           % Update x0 with latest value
end


%% Lab 4

f =  @(x) 2^x - 5*x + 2;
df = @(x) 2^x * log(2) - 5;
x0 = 0;        
e = 1e-4;
n = 10;


if df(x0) ~= 0

    for i = 1:n

        x1=x0-f(x0)/df(x1);
        fprintf('x%d = %.4f \n',i,x1);
        
        if abs(x1-x0)<e

        break
        
        end

        x0=x1;

    end

else

disp('Newton Raphson Method Failed');

end

%% Lab 5 

X = input('Enter abcissas: ');
Y = input('Enter ordinates: ');
P0 = input ('Enter the point at which you want approximation: ');
n = length(X);
L = zeros(n,n);

for i = 1:n % For rows
 V = 1;
    for j = 1:n % For making polynomials
        if i ~= j
            V = conv(V,poly(X(j)))/(X(i)-X(j))
        end
    end

    L(i,:) = V*Y(i);
end
L
P = sum(L);
F = flip(P);
disp('Your polynomial is:  ')
for k= n: -1 : 2
    fprintf('+ %.2fx^%d',F(k),k-1)
end
fprintf('+ %.2f\n',F(1))

A = polyval(P,P0);
disp('Approximate value of given point is : ')
