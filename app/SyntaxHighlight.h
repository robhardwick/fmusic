#ifndef FMUSIC_APP_SYNTAX_HIGHLIGHT_H
#define FMUSIC_APP_SYNTAX_HIGHLIGHT_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

namespace fMusic {
namespace App {

    class SyntaxHighlight : public QSyntaxHighlighter {
        Q_OBJECT

        public:
            SyntaxHighlight(QTextDocument *parent = 0);

        protected:
            void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

        private:
            struct HighlightingRule {
                QRegExp pattern;
                QTextCharFormat format;
            };

            QVector<HighlightingRule> highlightingRules;

            QRegExp commentStartExpression;
            QRegExp commentEndExpression;

            QTextCharFormat keywordFormat;
            QTextCharFormat commentFormat;
            QTextCharFormat quotationFormat;
            QTextCharFormat functionFormat;
    };

}
}

#endif
