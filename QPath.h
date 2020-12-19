#ifndef QPATH_H
#define QPATH_H

#include <QDir>
#include <QDebug>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QString>
#include <QSysInfo>

class QPath : public QString
{
public:
    enum Filter {
        Dirs = QDir::Dirs,
        AllDirs = QDir::AllDirs,
        Files = QDir::Files,
        Drives = QDir::Drives,
        NoSymLinks = QDir::NoSymLinks,
        NoDotAndDotDot = QDir::NoDotAndDotDot,
        NoDot = QDir::NoDot,
        NoDotDot = QDir::NoDotDot,
        AllEntries = QDir::AllEntries
    };

    enum SortFlags {
        Name = QDir::Name,
        Time = QDir::Time,
        Size = QDir::Size,
        Type = QDir::Type,
        Unsorted = QDir::Unsorted,
        NoSort = QDir::NoSort,
        DirsFirst = QDir::DirsFirst,
        DirsLast = QDir::DirsLast,
        Reversed = QDir::Reversed,
        IgnoreCase = QDir::IgnoreCase,
        LocaleAware = QDir::LocaleAware
    };

    
    QPath();
    QPath(const QString &other);

    // accessors
    QString name() const;
    QString stem() const;
    QString suffix() const;
    QPath parent(const int index = 0) const;

    // information
    bool exists() const;
    bool isDir() const;
    bool isFile() const;
    bool isSymlink() const;
    bool match(const QString &pattern) const;
    
    // navigation
    QList<QPath> iter(QStringList &nameFilters, Filter filters = AllEntries, SortFlags sort = NoSort) const; // add filters
    
    // actions
    QPath join(const QString &path) const;
    bool mkdir(const bool parents = true) const;
    QPath valid();
        
    // operators
    QPath operator/(const QString &path) const;
    
    // static methods
    static QPath cwd();

    // standard paths
    static QPath home();

private:
    QDir m_dir;
    QFileInfo m_fileInfo;

    QStringList m_parts;

    bool windows = QSysInfo::productType() == "windows";
    QString m_sep = windows ? "\\" : "/";
};

inline QPath::Filter operator|(QPath::Filter a, QPath::Filter b) {
    return static_cast<QPath::Filter>(static_cast<int>(a) | static_cast<int>(b));
}

#endif // QPATH_H
