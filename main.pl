% Prolog Project
% Liam McMahan
% 12-4-19
% CSC 344

% Sraight movement
straight([X,Y,r],[X2, Y, r]) :- X2 is X+1.
straight([X,Y,u],[X, Y2, u]) :- Y2 is Y-1.
straight([X,Y,d],[X, Y2, d]) :- Y2 is Y+1.

% Turning motion, relative to the direction and mirror orientation
turn([X,Y,r,/],[X,Y,u]).
turn([X,Y,u,/],[X,Y,r]).
turn([X,Y,r,\],[X,Y,d]).
turn([X,Y,d,\],[X,Y,r]).

% Safety methods
% Obstacle safety
isOutsideO([A,B,_],[X,W,H]) :- B>=H;A=<X;A>=X+W.
% Confirm that we are inside the grid
inGrid([A,B,_]) :- A>=0,A=<12,B>=0,B=<10.
% Safety relative to all obstacles
safe(State,[]) :- inGrid(State).
safe(State,[CurrentObstacle|Rest]) :-
    isOutsideO(State,CurrentObstacle),
    safe(State,Rest).

% Not member method for mirror handling (Used from class example)
notMember(_,[]):-!.
notMember(X,[Head|Tail]):-
    X\=Head,
    notMember(X,Tail).

% Next move methods
% Straight movement
nextMove(State,Obstacles,Mirrors,Mirrors,NewState):-
    straight(State,NewState),
    safe(NewState,Obstacles).
% Mirror placement
nextMove([X,Y,Dir],Obstacles,Mirrors,[[X,Y,Orientation]|Mirrors],NewestState):-
    turn([X,Y,Dir,Orientation],NewState),
    notMember([X,Y,Orientation],Mirrors),
    straight(NewState,NewestState),
    safe(NewestState,Obstacles).

% Detector state
detected([12,Y,r],Height) :-
    Y is Height.

% Human checking
human(3).
human(4).
human(5).
human(6).
human(7).
human(8).
humanCheck([A,B,_],HumanX):-
    (A=<HumanX;A>=HumanX+2;B=<4).

% Laser traversal to handle movement through out the map
% Base Case: Such that our nextmove will hit the detector correctly.
laserTraversal(State,Height,Obstacles,Mirrors,NewMirrors,_,_) :-
    nextMove(State,Obstacles,Mirrors,NewMirrors,NewState),
    detected(NewState,Height).
% Recursive Case: Such that we haven't hit the detector correctly yet
% and have yet to lose human space and/or use more than 8 mirrors.
laserTraversal(State,Height,Obstacles,Mirrors,EndMirrors,Path,Human) :-
    nextMove(State,Obstacles,Mirrors,NewMirrors,NewState),
    length(NewMirrors,L),
    L=<8,
    humanCheck(NewState,Human),
    laserTraversal(NewState,Height,Obstacles,NewMirrors,EndMirrors,[NewState|Path],Human).

% Height Conversion for the sake of demoing (added this in after I
% "half-demoed" this assignment that one time)
convertHeight(Height,NewHeight):-
    NewHeight is 10-Height.

% Place mirrors method to call laserTraversal with only the specified
% inputs.
placeMirrors(Height,Obstacles,EndMirrors) :-
    convertHeight(Height,NewHeight),
    human(Human),
    laserTraversal([1,NewHeight,r],NewHeight,Obstacles,[],EndMirrors,[[1,NewHeight,r]],Human).














