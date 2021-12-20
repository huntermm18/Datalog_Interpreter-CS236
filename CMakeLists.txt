cmake_minimum_required(VERSION 3.17)
project(Project1_Starter_Code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project1_Starter_Code
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        input.txt
        Lexer.cpp
        Lexer.h
        main.cpp
        MatcherAutomaton.cpp
        MatcherAutomaton.h
        Token.cpp
        Token.h
        IdentifierAutomaton.cpp
        IdentifierAutomaton.h
        StringAutomaton.cpp
        StringAutomaton.h
        CommentAutomaton.cpp
        CommentAutomaton.h
        makefile
        NoLongerNeeded/1-70
        __MACOSX
        NoLongerNeeded/1-90
        NoLongerNeeded/1-100
        DatalogProgram.h
        DatalogProgram.cpp
        Rule.cpp
        Rule.h
        Predicate.cpp
        Predicate.h
        Parameter.h
        Parser.cpp
        Parser.h
        Tuple.h
        Relation.cpp
        Relation.h
        Database.h
        Header.h
        Interpreter.cpp
        Interpreter.h
        Graph.cpp
        Graph.h)
