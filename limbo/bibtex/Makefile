all: web cv

# test web 
web: bibconvert.py test/Top.bib test/publications.bib 
	@echo "test web"
	@python bibconvert.py --suffix web --highlight "Yibo Lin" --highlight "Lin, Yibo" --input ./test/Top.bib --input ./test/publications.bib 

# test cv 
cv: bibconvert.py test/Top.bib test/publications.bib 
	@echo "test cv"
	@python bibconvert.py --suffix cv --highlight "Yibo Lin" --highlight "Lin, Yibo" --input ./test/Top.bib --input ./test/publications.bib 
