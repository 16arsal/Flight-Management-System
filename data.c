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

        x1=x0-f(x0)/df(x0);
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

%%
function [P, coeffs] = lagrange_poly(x_data, y_data)
    n = length(x_data);
    syms x;

    P = 0;

    for i = 1:n
        L = 1;
        for j = 1:n
            if i~=j
                L = L * (x-x_data(j))/(x_data(i) - x_data(j));
            end
        end
        P = P + y_data(i)*L;
    end
    P = expand(P);
    coeffs = sym2poly(P);
end

%%

x_data = input('Enter the x data points as a vector (e.g. [1 2 3]): ');
y_data = input('Enter the y data points as a vector (e.g. [4 5 6]): ');

if length(x_data) ~= length(y_data)
    error('x_data and y_data must have the same length.');
end

x_points = input('Enter the x values (vector) where you want to evaluate the polynomial (e.g. [1.5 2.5 3.7]): ');

[poly, ~] = lagrange_poly(x_data, y_data);

disp('Symbolic view of polynomial:');
pretty(poly);

y_points = double(subs(poly, x_points));

figure;
fplot(poly, [min(x_data)-1, max(x_data)+1], 'LineWidth', 1.5);
hold on;

stem(x_data, y_data, 'filled', 'b');

stem(x_points, y_points, 'r');

hold off;
grid on;
grid minor;
legend('Lagrange Polynomial', 'Original Data Points', 'Interpolated Points');

for k = 1:length(x_points)
    fprintf('For x = %.4g, interpolated y = %.4g\n', x_points(k), y_points(k));
end

%% lab 6 and 7 
%% Lagrange Interpolation

X = input('Enter abscissas: ');
Y = input('Enter ordinates: ');
P0 = input('Enter the point at which you want approximation: ');

n = length(X);
L = zeros(n,n);

for i = 1:n        % Loop for each Lagrange basis
    V = 1;
    for j = 1:n
        if i ~= j
            V = conv(V, poly(X(j))) / (X(i) - X(j));
        end
    end
    L(i,:) = V * Y(i);
end

P = sum(L);        % Final polynomial coefficients
F = flip(P);

disp('Interpolating polynomial is:')
for k = n:-1:2
    fprintf('+ %.2fx^%d ', F(k), k-1)
end
fprintf('+ %.2f\n', F(1))

A = polyval(P, P0);
disp('Approximate value at given point is:')
disp(A)


%% Newton Forward 


x = input('Enter x values: ');
y = input('Enter y values: ');
xp = input('Enter x at which y is required: ');

n = length(x);
h = x(2) - x(1);
uniform = true;

for i = 2:n-1
    if abs((x(i+1) - x(i)) - h) > 1e-6
        uniform = false;
        break;
    end
end

if ~uniform
    disp('x-values are NOT equally spaced.');
    disp('Newton Forward Interpolation NOT applicable.');
    return;
end

disp('x-values are equally spaced.');
disp('Applying Newton Forward Interpolation...');


D = zeros(n,n);
D(:,1) = y';

for j = 2:n
    for i = 1:n-j+1
        D(i,j) = D(i+1,j-1) - D(i,j-1);
    end
end

disp('Forward Difference Table:');
disp(D);

p = (xp - x(1)) / h;
yp = D(1,1);

p_term = 1;
fact = 1;

for i = 1:n-1
    p_term = p_term * (p - (i-1));
    fact = fact * i;
    yp = yp + (p_term/fact) * D(1,i+1);
end

fprintf('\nFinal Result:\n');
fprintf('y(%.4f) = %.6f\n', xp, yp);

