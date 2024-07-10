// Config
// {
//     "theme": "neutral"
// }

flowchart LR
    classDef default stroke:black;
    linkStyle default stroke-width:1px, stroke:black;

    // 160_example_1_1
    A: ~~~~ F1((4))--> O1((1))-->E((8))-->F((4))-->Fi((5))
    B: ~~~ F2((5))-->S((6))-->O2((1))-->E

    // 160_example_2
    A: ~~~ O1((1))--> N1((9))-->O2((1))-->T((2))-->F((4))
    B: ~~~~~ Tr((3))-->T

    // 160_example_3
    A: ~~~ T1((2))--> S1((6))-->F1((4))
    B: ~~~~ O2((1))-->F2((5))


// %% 24_drawing_1
A((prev))--> B((cur))-->C((next))-->D((" "))-->E((" "))
A1((prev))~~~B1((cur))~~~C1((next))~~~D1((" "))-->E1((" "))
A1-->C1-->B1-->D1


// %% 141_circularlinkedlist
A((3))--> B((2))-->C((0))-->D(("-4"))-->B
// %% 141_circularlinkedlist_test2
    A((1))--> B((2))-->A

// %% 141_circularlinkedlist_test3
    A((1))
    
%% 876_lc-midlist1
    %% A((1))--> B((2))-->C((3))-->D((4))-->E((5))

    %% style C fill:#aaa, stroke-width:2px, stroke:black;

%% 876_lc-midlist2
    %% A((1))--> B((2))-->C((3))-->D((4))-->E((5))-->F((6))
    
    %% style D fill:#aaa, stroke-width:2px, stroke:black;
