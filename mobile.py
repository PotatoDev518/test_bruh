
# pip install wget PyMuPDF

from requests import get
from bs4 import BeautifulSoup as soupify
from wget import download
import os
import fitz

def get_pdfs_from_url(url):
    soup = soupify(get(url).content )
    for raw_url in soup.find_all("a"):
        link = raw_url.get("href")
        if str(link).endswith(".pdf"):
            
            try:
                download(link, out=os.path.join(  os.getcwd() , "pdfs"  ))
                
            except Exception  as e:
                print(e)
                
def text_from_pdf(pdf_path):
    doc = fitz.open(pdf_path)
    yield f"{pdf_path}:             " + "('\n' * 5)"
    for page in doc:
        yield str(page.get_text().strip())


ENCODING = "utf-32"

def pdfs_to_txt(outpath="pdfs"):
    with open("output.txt", "w",encoding=ENCODING) as f:
        path = os.path.join(os.getcwd(), outpath)
        if os.path.exists(path):
            for pdf in os.listdir(path):
                
                for text in text_from_pdf(os.path.join(os.getcwd(), path , pdf)):
                    
                    try:
                        f.write(text)
                    except Exception as e:
                        print(e)
                print("one done")


if __name__ == "__main__":
    get_pdfs_from_url("https://www.hubeali.com/online-books/online-english-books/bihar-al-anwaar/")
    pdfs_to_txt()
