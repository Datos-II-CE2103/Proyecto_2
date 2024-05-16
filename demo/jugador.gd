extends CharacterBody2D

@export var speed = 40

@onready var player_animation = $CollisionShape2D/AnimatedSprite2D
func update_animations():
	if velocity.x > 0:
		player_animation.play("derecha")
		#print(velocity)
	elif velocity.x < 0:
		player_animation.play("izquierda")
		#print(velocity)
	elif velocity.y < 0:
		player_animation.play("arriba")
		#print(velocity)
	elif velocity.y > 0:
		player_animation.play("abajo")
		#print(velocity)
	else:
		player_animation.stop();
		

func get_input():
	var input_direction = Input.get_vector("ui_left", "ui_right", "ui_up", "ui_down")
	velocity = input_direction *speed

func _physics_process(delta):
	get_input()
	move_and_slide()
	update_animations()
	
