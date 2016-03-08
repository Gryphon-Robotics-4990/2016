#Code for 4990 2016

##Documentaton for Autonomous

Place all commands below in the AutoDriveController::run function

###Commands

rb->travel(metres) where metres is the metres wanted to travel. Postive is forwards, negative is backwards.

rb->turn(degrees) where degrees is the degrees wanted to turn. Positive is clockwise, negative is counterclockwise.

rb->wait(seconds) where seconds is the amount of seconds to wait.


####The commands below can be run in conjunction with the commands above!

rb->intake(timeout). This will keep intaking until the limitswitch is triggered or the timeout is reached.

rb->expell(timeout). This will expell until the timeout is reached. 

