#include "QPath.h"

QPath::QPath()
    : QString(),
      m_dir(QDir()),
      m_fileInfo(QFileInfo())
{

}

QPath::QPath(const QString &path)
    : QString(path),
      m_dir(QDir(path)),
      m_fileInfo(QFileInfo(path))
{
   m_parts = m_fileInfo.absoluteFilePath().split(m_sep, QString::SkipEmptyParts);
}


QString QPath::name() const {
    return m_parts.last();
}

QString QPath::stem() const {
    return m_fileInfo.completeBaseName();
}

QString QPath::suffix() const {
    return m_fileInfo.suffix();
}

QPath QPath::parent(const uint index) const {
    if (index < m_parts.size() - 1) {
        QStringList prefix();
        for (int i = 0; i < m_parts.size() - 1 - index; ++i) {
            prefix.append(m_parts.at(i));
        }
        return QPath(prefix.join(m_sep));
    }
    qDebug() << "QPath::parent(): "
                "Tried to access parent" << index << "of a path of depth" << m_parts.size();
    return QPath();
}


bool QPath::exists() const {
    return m_fileInfo.exists();
}

bool QPath::isDir() const {
    return m_fileInfo.isDir();
}

bool QPath::isFile() const {
    return m_fileInfo.isFile();
}

bool QPath::isSymlink() const {
    return m_fileInfo.isSymLink();
}

bool QPath::match(const QString &pattern) const {
    QRegularExpression re(pattern);
    return re.match(*this).hasMatch();

}


QPathList QPath::iter(QStringList &nameFilters, QPath::Filter filters, QPath::SortFlags sort) const {
    paths = QPathList();
    if (!isDir()) {
        qDebug() << "QPath::iter():"
                 << *this << "is not a valid directory";
        return paths;
    }
    for (QString &entry : m_dir.entryList(nameFilters, filters, sort))
        paths.append(QPath(entry));
    return paths;
}


QPath QPath::join(const QString &path) const {
    return QPath(m_dir.absoluteFilePath(path));
}


QPath QPath::operator/(const QString &path) {
    return join(path);
}


QPath QPath::cwd() {
    return QPath(QDir::currentPath());
}

QPath QPath::home() {
    return QPath(QStandardPaths::displayName(QStandardPaths::HomeLocation));
}
