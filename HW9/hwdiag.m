function A = hwdiag(n)

A = zeros(n,n)

if n > 1
    for c = 1:n
        for r = 1:n
            if r == c + 1
                A(r,c) = c;
            elseif r == c - 1
                A(r,c) = n - r;
            else
                A(r,c) = 0;
            end
        end
    end
end