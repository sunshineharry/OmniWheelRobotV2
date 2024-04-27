function rosmsgOut = TwistWithCovariance(slBusIn, rosmsgOut)
%#codegen
%   Copyright 2021 The MathWorks, Inc.
    rosmsgOut.twist = bus_conv_fcns.ros2.busToMsg.geometry_msgs.Twist(slBusIn.twist,rosmsgOut.twist(1));
    rosmsgOut.covariance = double(slBusIn.covariance);
end
