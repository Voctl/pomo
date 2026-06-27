PREFIX ?= /usr/local

comp:
	mkdir -p build
	gcc src/pomo.c -o build/pomo

run:
	./build/pomo

install: comp
	@echo "Installing pomo binary to $(PREFIX)/bin..."
	sudo cp build/pomo $(PREFIX)/bin/pomo
	sudo chmod +x $(PREFIX)/bin/pomo
	
	@echo "Installing i3status wrapper scripts to ~/.config/i3..."
	mkdir -p ~/.config/i3
	cp i3/statusw.py ~/.config/i3/statusw.py
	cp i3/statusw.sh ~/.config/i3/statusw.sh
	chmod +x ~/.config/i3/statusw.py
	chmod +x ~/.config/i3/statusw.sh
	
	@echo "Applying fixes to i3status configuration..."
	@if [ -f ~/.config/i3status/config ]; then \
		sed -i 's/\btz local/tztime local/g' ~/.config/i3status/config; \
	fi
	
	@echo "Reloading i3 configuration..."
	i3-msg reload
	
	@echo "Installation complete!"
