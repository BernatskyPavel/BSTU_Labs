from spacy.lang.ru import Russian

nlp = Russian()
doc = nlp("Съешь ещё этих мягких французских булок, да выпей чаю.")

token = doc[0]
print(token.text)

span = doc[3:6]
print(span.text)

print(f"is_alpha:     {[token.is_alpha for token in doc]}\n"
      f"is_punct:     {[token.is_punct for token in doc]}\n"
      f"like_num:     {[token.like_num for token in doc]}")

for token in doc:
    if token.i + 1 < len(doc):
        next_token = doc[token.i + 1]
        if next_token.text == ".":
            print(token.text)

import spacy

nlp = spacy.load("en_core_web_sm")
doc = nlp("New Apple MacBook set launch tomorrow")

for token in doc:
    token_text = token.text
    token_pos = token.pos_
    token_dep = token.dep_
    token_head = token.head.text
    print(f"{token_text:<12}{token_pos:<10}"
          f"{token_dep:<10}{token_head:<12}")

from spacy import displacy
from pathlib import Path

svg = displacy.render(doc, style='dep')
output_path = Path("./Lab-12/sentence.svg")
output_path.open("w", encoding="utf-8").write(svg)

print(spacy.explain('aux'))
print(spacy.explain('PROPN'))

doc = nlp("I saw a movie yesterday")
print(' '.join([token.lemma_ for token in doc]))

doc = nlp("Apple is looking at buying U.K. startup for 1$ billion")
for ent in doc.ents:
    print(ent.text, ent.label_)

print(spacy.explain("GPE"))
svg = displacy.render(doc, style='ent')
output_path = Path("./Lab-12/apple.svg")
output_path.open("w", encoding="utf-8").write(svg)

from spacy.matcher import Matcher

matcher = Matcher(nlp.vocab)
pattern = [{
    "IS_DIGIT": True
}, {
    "LOWER": {
        "REGEX": "(fifa|icc)"
    }
}, {
    "LOWER": "cricket",
    "OP": "?"
}, {
    "LOWER": "world"
}, {
    "LOWER": "cup"
}]
matcher.add("fifa_pattern", [pattern], on_match=None)
doc = nlp("2018 ICC Cricket World Cup: Afghanistan won!")
matches = matcher(doc)
for match_id, start, end in matches:
    matched_span = doc[start:end]
    print(matched_span)

nlp = spacy.load("en_core_web_md")
doc1 = nlp("I like burgers")
doc2 = nlp("I like pizza")
print(doc1.similarity(doc2))