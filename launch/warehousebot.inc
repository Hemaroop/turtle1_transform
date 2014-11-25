include "sick.inc"

define warehouse_cart position
(
  drive "diff"
  gui_nose 1
  obstacle_return 1
  ranger_return 0.5
  blob_return 0
  fiducial_return 1
  localization "odom"
  localization_origin [0 0 0 0]
  odom_error [0.05 0.05 0 0.1]
  velocity_bounds [-2.5 2.5 0 0 0 0 -90.0 90.0]
  acceleration_bounds [-0.5 0.5 0 0 0 0 -90.0 90.0]
  mass 20.0
)

define cart_stand_offs model
(
  color "black"
  obstacle_return 1
  blob_return 1
  block 
  (
    points 16
    point[0] [1 0]
    point[1] [0.924 0.382]
    point[2] [0.707 0.707]
    point[3] [0.382 0.924]
    point[4] [0 1]
    point[5] [-0.382 0.924]
    point[6] [-0.707 0.707]
    point[7] [-0.924 0.382]
    point[8] [-1 0]
    point[9] [-0.924 -0.382]
    point[10] [-0.707 -0.707]
    point[11] [-0.382 -0.924]
    point[12] [0 -1]
    point[13] [0.382 -0.924]
    point[14] [0.707 -0.707]
    point[15] [0.924 -0.382]
    z [0 1]
  )
  size [ 0.02 0.02 0.458 ]
)

define cart_plate model
(
  color "snow"
  obstacle_return 1
  ranger_return 0.5
  blob_return 1
  block 
  (
    points 4
    point[0] [ 0.350 0.305 ]
    point[1] [ -0.350 0.305 ]
    point[2] [ -0.350 -0.305 ]
    point[3] [ 0.350 -0.305 ]
    z [0 0.01]
  )
  size [0.700 0.610 0.01]
)

define cart_no_sensor warehouse_cart
(
  color "gray50"
  size [ 0.766 0.610 0.458]
  block 
  (
    points 4
    point[0] [ 0.383 0.305 ]
    point[1] [ -0.383 0.305 ]
    point[2] [ -0.383 -0.305 ]
    point[3] [ 0.383 -0.305 ]
    z [0 0.458]
  )
)

define warehouse_bot cart_no_sensor
(
  cart_plate
  ( 
    pose [-0.033 0 0.01 0 ]
    cart_stand_offs( pose [ 0.33 0.28 0 0 ] )
    cart_stand_offs( pose [ -0.33 0.28 0 0 ] )
    cart_stand_offs( pose [ -0.33 -0.28 0 0 ] )
    cart_stand_offs( pose [ 0.33 -0.28 0 0 ] )
    fancysicklaser
    (
      pose [ 0.25 0.0 0.0 0.0 ]
    )
    cart_plate
    ( 
      pose [0 0 0.458 0]
      cart_stand_offs( pose [ 0.33 0.28 0 0 ] )
      cart_stand_offs( pose [ -0.33 0.28 0 0 ] )
      cart_stand_offs( pose [ -0.33 -0.28 0 0 ] )
      cart_stand_offs( pose [ 0.33 -0.28 0 0 ] )  
      cart_plate
      ( 
        pose [0 0 0.458 0]
        cart_stand_offs( pose [ 0.33 0.28 0 0 ] )
        cart_stand_offs( pose [ -0.33 0.28 0 0 ] )
        cart_stand_offs( pose [ -0.33 -0.28 0 0 ] )
        cart_stand_offs( pose [ 0.33 -0.28 0 0 ] )
        cart_plate
        ( 
          pose [0 0 0.458 0]
          blobfinder
          (
	    name "blobcam1"
	    color "black"
            pose [ 0.30 0.0 0.04 0.0 ]
	    colors_count 15
	    colors [ "red" "green" "blue" "chocolate1" "violet" "cyan1" "yellow1" "firebrick1" "magenta" "purple1" "pink" "DebianRed" "maroon1" "brown1" "sienna1" ]
            image [ 600 600 ]
            fov 60.0
            range 5.0
	    #pantilt [ 0 45 ]
          ) 
          
          #camera
          #(
	  #  name "cam2"
          #  pose [ 0 -0.25 0.04 0.0 ]
          #  resolution [ 700 500 ]
          #  fov [ 70 50 ]
          #  range [ 0.2 9.0 ]
          #) 
        )  
      )
    )
  )
)
