import RPi.GPIO as GPIO
#GPIO.setwarnings(False)
#GPIO.cleanup()

# Setup Pins
PWM_A = 15
PWM_B = 33
BIN1 = 12
BIN2 = 11
STBY = 13
AIN1 = 18
AIN2 = 16

class Motor:
	def __init__(self):
		GPIO.setmode(GPIO.BOARD)
		GPIO.setup(PWM_A, GPIO.OUT)
		GPIO.setup(STBY, GPIO.OUT)
		GPIO.setup(AIN1, GPIO.OUT)
		GPIO.setup(AIN2, GPIO.OUT)
		GPIO.output(STBY, GPIO.HIGH)
		
	def drive(self, forward, speed):
		GPIO.output(AIN1, not forward)
		GPIO.output(AIN2, forward)
		self.p = GPIO.PWM(PWM_A, speed)
		self.p.start(0.1)
		

if __name__ == "__main__":
	motor = Motor()
	motor.drive(True, 50000)

	try:
		while True:
			pass
	except KeyboardInterrupt:
		print("\nclean up")
	finally:
		GPIO.cleanup()
