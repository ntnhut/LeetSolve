# Configuration file for the Sphinx documentation builder.

# -- Project information

# If you want smaller code font size
# from sphinx.highlighting import PygmentsBridge
# from pygments.formatters.latex import LatexFormatter

# class CustomLatexFormatter(LatexFormatter):
#     def __init__(self, **options):
#         super(CustomLatexFormatter, self).__init__(**options)
#         self.verboptions = r"formatcom=\footnotesize"

# PygmentsBridge.latex_formatter = CustomLatexFormatter

project = 'LeetSolve'
copyright = '2024, Nhut Nguyen'
author = 'Nhut Nguyen'

version = '1.3.0'

# -- General configuration

extensions = [
    'myst_parser',
    'sphinx.ext.duration',
    'sphinx.ext.doctest',
    'sphinx.ext.autodoc',
    'sphinx.ext.autosummary',
    'sphinx.ext.intersphinx',
    'sphinx.ext.mathjax',
]

myst_enable_extensions = ["dollarmath", "amsmath", "smartquotes"]

intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'sphinx': ('https://www.sphinx-doc.org/en/master/', None),
}
intersphinx_disabled_domains = ['std']

templates_path = ['_templates']

book_format = 'html'
# book_format = 'paperback'
# book_format = 'pdf'

if book_format is 'html':
    master_doc = 'index_10'
else:
    master_doc = 'index_book1'
    

exclude_patterns = ['*/index_*.rst']

# -- Options for HTML output

html_theme = "furo"
html_logo = "img/logo_name.svg"
if book_format is 'paperback':
    pygments_style = 'bw' # bw stands for black and white, for print

html_theme_options = {
    # 'logo_only': True,
    "sidebar_hide_name": True,
    # 'nosidebar': True,
    "announcement": "Support my work by buying my book <a href='https://theproblemsolversguidetocoding.com'  target='_blank'>here</a>!", 
}

source_suffix = {
    '.rst': 'restructuredtext',
    '.md': 'markdown',
}

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',
    'sphinxsetup': 'hmargin={2cm,2cm}, vmargin={2cm,2cm}',

    # The font size ('10pt', '11pt' or '12pt').
    #
    'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    #
    'preamble': r'''
    \usepackage{charter}
    \usepackage[defaultsans]{lato}
    \usepackage{inconsolata}
    \definecolor{TitleColor}{rgb}{0,0,0}
    \definecolor{InnerLinkColor}{rgb}{0,0,0}
    \usepackage[paperwidth=17cm,paperheight=22cm]{geometry}
    \addto\captionsenglish{\renewcommand{\contentsname}{Contents}}
    \setcounter{tocdepth}{1}
    ''',
    # uncomment these in preamble for print
    # \definecolor{TitleColor}{rgb}{0,0,0}
    # \definecolor{InnerLinkColor}{rgb}{0,0,0}


    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',        
}
# turn on footnote for print book
if book_format is 'paperback':
    latex_show_urls = 'footnote'

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
# latex_documents = [
#     (master_doc, 'leetsolve.tex', '10 Classic Coding Challenges',
#      'Nhut Nguyen, Ph. D.', 'howto'),
# ]
latex_documents = [
    (master_doc, 'leetsolve.tex', 'The Problem Solver\'s Guide To Coding',
     'Nhut Nguyen, Ph. D.', 'book'),
]
latex_docclass = {
   'book': 'book',
}
