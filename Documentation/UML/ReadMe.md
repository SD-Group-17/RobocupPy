# UML Diagrams

## Figure 1
![Diagram 1](https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/UML/img1.jpeg) \
\
A State Machine is a structure that describes state-dependent behaviour for an object and the transitions between each state are the process that the coder or the server does. As one can see the first action/process leads to the first state, Singularity Ready, and the last state, Returned Skill State, is terminated when the game is ended. 

## Figure 2
![Diagram 2](https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/UML/img2.jpeg) \
\
A Deployment diagram shows the configuration of run time processing nodes and the components that live on them. In the context of Robocup the only node we are looking at is the client’s computer, with the various artefacts that make it up being, User's Python
Code, Singularity Terminal, Austin Texas Library and Server (runs on singularity). 

## Figure 3
![Diagram 3](https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/UML/img3.jpeg) \
\
User Stories are stated ideas of requirements that express what users need. The arrows from the user show what needs or provides in the context of the wrapper.

## Figure 4
![Diagram 4](https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/UML/img4.jpeg) \
\
A Component diagram that models the physical aspects of object-oriented systems that are used for visualizing, specifying, and documenting component-based systems and focus on a system's components that often used to model the static implementation view of a system. Each block in the diagram describes a component with the open-cup transition showing the required interface and the ball head transition showing the provided interface. The text next to the interface describes what exactly is provided.

## Figure 5
![Diagram 5](https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/UML/img5.jpeg) \
\
A Process diagram describes how activities are coordinated to provide a service which can be at different levels of the state lifeline, so it the basically the transitions of the state machine on a different diagram. The first activity is the running of ‘./robocup-mesa’ leading to a chain of events and ending with the ending of the game.

## Figure 6
![Diagram 6](https://github.com/SD-Group-17/RobocupPy/blob/master/Documentation/UML/img6.jpeg) \
\
A Class Diagram is a type of static structure diagram that describes the structure of the wrapper system. In this case we have only one central class for wrapper, which is the Robocup class. The top half of the diagram describes the attributes of the class, which are all public, and the bottom describes the methods of the class
