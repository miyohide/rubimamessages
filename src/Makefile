all: pdf

pdf:
	rm -rf book book-pdf book.pdf
	review-pdfmaker config.yml

epub:
	rm -rf book book-epub book.epub
	review-epubmaker config.yml

clean:
	rm -rf book book-epub book-pdf book.pdf book.epub
