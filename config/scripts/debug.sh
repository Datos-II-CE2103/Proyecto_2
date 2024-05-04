#!/bin/bash
scons
scons target=template_release
scons target=editor
./Godot422 --path ./demo


