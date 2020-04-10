void obstacleAvoidance() {
  
  int distance = front.getDistance();

  if (distance <= 15 && distance > 0){ //stop when distance is less than 15 cm.
  car.setSpeed(0);
  }
  else{
    // Move forward in speed of 40% of the capacaty 
    car.setSpeed(40);
  }
  
}
