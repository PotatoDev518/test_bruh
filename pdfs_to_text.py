import os
import fitz


ENCODING = "utf-32"

def text_from_pdf(pdf_path):
    doc = fitz.open(pdf_path)
    yield f"{pdf_path}:             " + "('\n' * 5)"
    for page in doc:
        yield str(page.get_text().strip())





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
    pdfs_to_txt()