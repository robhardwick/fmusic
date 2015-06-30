#include "SyntaxHighlight.h"

using namespace fMusic::App;

/**
 * Initialise syntax highlight rules
 */
SyntaxHighlight::SyntaxHighlight(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {

    HighlightingRule rule;

    // Lua keywords
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\band\\b" << "\\bbreak\\b" << "\\bdo\\b"
                    << "\\belse\\b" << "\\belseif\b" << "\\bend\\b"
                    << "\\bfalse\\b" << "\\bfor\\b" << "\\bfunction\\b"
                    << "\\bif\\b" << "\\bin\\b" << "\\blocal\\b"
                    << "\\bnil\\b" << "\\bnot\\b" << "\\bor\\b"
                    << "\\brepeat\\b" << "\\breturn\\b" << "\\bthen\\b"
                    << "\\btrue\\b" << "\\buntil\\b" << "\\bwhile\\b";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Lua comments
    commentFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("--[^\n]*");
    rule.format = commentFormat;
    highlightingRules.append(rule);

    // Lua strings
    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"|'.*'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // Lua functions
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
}

/**
 * Apply syntax highlight rules
 */
void SyntaxHighlight::highlightBlock(const QString &text) {
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
}
