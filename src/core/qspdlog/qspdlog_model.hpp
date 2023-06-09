#pragma once

#include "QAbstractListModel"
#include "deque"
#include "optional"

class QSpdLogModel : public QAbstractListModel {
public:
Q_OBJECT
public:
    struct entry_t {
        std::chrono::duration<double> time;
        size_t thread_id;
        int level;
        std::string message;
        std::string loggerName;
    };
public:
    explicit QSpdLogModel(QObject *parent = nullptr);

    ~QSpdLogModel() override = default;

    void addEntry(entry_t entry);

    void clear();

    void setMaxEntries(std::optional<std::size_t> maxEntries);

    std::optional<std::size_t> getMaxEntries() const;

    void setLoggerForeground(std::string_view loggerName, std::optional<QColor> color);

    std::optional<QColor> getLoggerForeground(std::string_view loggerName) const;

    void setLoggerBackground(std::string_view loggerName, std::optional<QBrush> brush);

    std::optional<QBrush> getLoggerBackground(std::string_view loggerName) const;

#pragma region QAbstractListModel

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

#pragma endregion
private:
    std::deque<entry_t> m_items;
    std::optional<std::size_t> m_maxEntries;
    std::map<std::string, QBrush> m_backgroundMappings;
    std::map<std::string, QColor> m_foregroundMappings;
};