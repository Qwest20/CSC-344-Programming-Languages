% Check if a point is inside the rectangle, given its starting point
% and its width and height. Form this as "We are inside the rectangle
% if... the point's X is in between the Rectangle's X and X+Width AND
% if the point's Y is in between the Rectangle's Y and Y-Height."
isInside(P,R):-
    % Define a point to with an A(X) coordinate and a B(Y) coordinate
    P=[A,B],
    % Define a list to represent our rectangle
    R=[X,Y,W,H],
    %X of the point is greater than X of the rectangle
    A>X,
    %X of the point is less than X+Width of the rectangle
    A<X+W+1,
    %Y of the point is greater than Y of the rectangle
    B>Y,
    %Y of the point is less than Y+Height of the rectangle
    B<Y+H+1.

