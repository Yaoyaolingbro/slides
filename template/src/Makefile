LECNO = 0
FLAGS = --scripts https://cdn.tonycrane.cc/heti/heti.js,heti_worker.js --template template.html
BASE_DIR = ../site

.PHONY: live build clean

live:
	@echo "Previewing main slides..."
	-@reveal-md main.md -w --scripts https://cdn.tonycrane.cc/heti/heti.js,heti_worker.js  || true

build:
	@echo "Building main slides..."
	@reveal-md main.md --scripts https://cdn.tonycrane.cc/heti/heti.js,heti_worker.js  --static ../site --assets-dir assets
	@rm ../site/main.html

print:
	@echo "Building print version of main slides..."
	@reveal-md main.md --scripts https://cdn.tonycrane.cc/heti/heti.js,heti_worker.js --print ../site/main.pdf

clean:
	@echo "Cleaning up..."
	rm -rf ../site/
