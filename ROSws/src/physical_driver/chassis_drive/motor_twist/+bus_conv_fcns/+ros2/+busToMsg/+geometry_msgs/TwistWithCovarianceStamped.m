function rosmsgOut = TwistWithCovarianceStamped(slBusIn, rosmsgOut)
%#codegen
%   Copyright 2021 The MathWorks, Inc.
    rosmsgOut.header = bus_conv_fcns.ros2.busToMsg.std_msgs.Header(slBusIn.header,rosmsgOut.header(1));
    rosmsgOut.twist = bus_conv_fcns.ros2.busToMsg.geometry_msgs.TwistWithCovariance(slBusIn.twist,rosmsgOut.twist(1));
end
