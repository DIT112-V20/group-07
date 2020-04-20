void obstacleAvoidance() {
  
  int distance = front.getDistance();

  if (distance <= 15 && distance > 0){ //stop when distance is less than 15 cm.
    stop();
  }
  else{
    // Move forward in speed of 40% of the capacaty 
    handleInput();
  }
  
}
