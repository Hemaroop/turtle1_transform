define warehouse_shelf model
(
  color "DarkSlateGrey"
  obstacle_return 1 
  blob_return 1
  size [ 10.0 0.80 2.0 ]
  block
  (
    points 4
    point[0] [ 5.0 0.4  ]
    point[1] [ -5.0 0.4 ]
    point[2] [ -5.0 -0.4 ]
    point[3] [ 5.0 -0.4 ]
    
    z [ 0 2.0 ]
  )
)