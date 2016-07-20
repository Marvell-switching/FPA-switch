# FPA-logical-switch

The Forwarding Plane Abstraction (FPA) logical switch model is an abstract
switch specialization for the Marvell® Prestera devices.

The FPA provides API calls to
support interrogating tables for certain capabilities. These capabilities can include supported match
fields, actions, instructions, and more. They can also include status properties, such as current
resource usage.
The FPA model proves to be an efficient and modular programming approach due to the controller’s
ability to optimize hardware resources better than the switch, and due to the fact that the controller
has more CPU power and memory than the control processor on a typical switch. The controller
recognizes the actions the application tries to perform, especially when the application requires
updating multiple tables.
