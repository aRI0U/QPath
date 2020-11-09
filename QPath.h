#ifndef QPATH_H
#define QPATH_H

#include <QDir>
#include <QStandardPaths>
#include <QString>
#include <QSysInfo>

class QPath : public QString
{
public:
    typedef QList<QPath> QPathList;

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
    QPath parent(const uint index = 0) const;

    // information
    bool exists() const;
    bool isDir() const;
    bool isFile() const;
    bool isSymlink() const;
    bool match(const QString &pattern) const;
    
    // navigation
    QPathList iter(QStringList &nameFilters, Filter filters, SortFlags sort) const; // add filters
    
    // actions
    QPath join(const QString &path) const;
        
    // operators
    QPath operator/(const QString &path) const;
    
static:
    QPath cwd();

    // standard paths
    QPath home();

private:
    const QDir m_dir;
    const QFileInfo m_fileInfo;

    const QStringList m_parts;

    const bool windows = QSysInfo::productType() == "windows";
    const QString m_sep = windows ? "\\" : "/";
};

#endif // QPATH_H
