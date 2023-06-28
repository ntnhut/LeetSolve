# Configuration file for the Sphinx documentation builder.

# -- Project information

from sphinx.highlighting import PygmentsBridge
from pygments.formatters.latex import LatexFormatter

class CustomLatexFormatter(LatexFormatter):
    def __init__(self, **options):
        super(CustomLatexFormatter, self).__init__(**options)
        self.verboptions = r"formatcom=\footnotesize"

PygmentsBridge.latex_formatter = CustomLatexFormatter

project = 'LeetSolve'
copyright = '2023, Nhut Nguyen'
author = 'Nhut Nguyen'

release = '0.6'
version = '0.6.0'

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

myst_enable_extensions = ["dollarmath", "amsmath"]

intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'sphinx': ('https://www.sphinx-doc.org/en/master/', None),
}
intersphinx_disabled_domains = ['std']

templates_path = ['_templates']

master_doc = 'index'
# -- Options for HTML output

html_theme = "furo"
html_logo = "img/logo_name.svg"
html_theme_options = {
    # 'logo_only': True,
    "sidebar_hide_name": True,
    # 'nosidebar': True,
}

source_suffix = {
    '.rst': 'restructuredtext',
    '.md': 'markdown',
}

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    'papersize': 'a4paper',

    # The font size ('10pt', '11pt' or '12pt').
    #
    'pointsize': '12pt',

    # Additional stuff for the LaTeX preamble.
    #
    'preamble': r'\addto\captionsenglish{\renewcommand{\contentsname}{Contents}}',

    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',        
}
latex_show_urls = 'footnote'

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
    (master_doc, 'leetsolve.tex', 'The Problem Solver\'s Guide To Coding',
     'Nhut Nguyen, Ph. D.', 'book'),
]
latex_docclass = {
   'book': 'book',
}
