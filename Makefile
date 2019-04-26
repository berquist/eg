.PHONY: test
test:
	python -m pytest -v

.PHONY: test-python
test-python:
	python -m pytest -v

.PHONY: test-python2
test-python2:
	python2 -m pytest -v
