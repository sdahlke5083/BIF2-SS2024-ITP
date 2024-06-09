using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Geld_Guardian.Migrations
{
    /// <inheritdoc />
    public partial class MoreBillModels : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Category",
                table: "bills");

            migrationBuilder.DropColumn(
                name: "PaymentMethod",
                table: "bills");

            migrationBuilder.DropColumn(
                name: "Status",
                table: "bills");

            migrationBuilder.DropColumn(
                name: "Category",
                table: "BillItems");

            migrationBuilder.AddColumn<int>(
                name: "CategoryId",
                table: "bills",
                type: "INTEGER",
                nullable: true);

            migrationBuilder.AddColumn<int>(
                name: "PaymentMethodId",
                table: "bills",
                type: "INTEGER",
                nullable: true);

            migrationBuilder.AddColumn<int>(
                name: "StatusId",
                table: "bills",
                type: "INTEGER",
                nullable: true);

            migrationBuilder.AddColumn<int>(
                name: "CategoryId",
                table: "BillItems",
                type: "INTEGER",
                nullable: true);

            migrationBuilder.CreateTable(
                name: "Categorie",
                columns: table => new
                {
                    CategorieId = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Name = table.Column<string>(type: "TEXT", nullable: true),
                    Description = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Categorie", x => x.CategorieId);
                });

            migrationBuilder.CreateTable(
                name: "PaymentMethod",
                columns: table => new
                {
                    PaymentId = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Name = table.Column<string>(type: "TEXT", nullable: true),
                    Description = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_PaymentMethod", x => x.PaymentId);
                });

            migrationBuilder.CreateTable(
                name: "PaymentStatus",
                columns: table => new
                {
                    StatusId = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Name = table.Column<string>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_PaymentStatus", x => x.StatusId);
                });

            migrationBuilder.CreateIndex(
                name: "IX_bills_CategoryId",
                table: "bills",
                column: "CategoryId");

            migrationBuilder.CreateIndex(
                name: "IX_bills_PaymentMethodId",
                table: "bills",
                column: "PaymentMethodId");

            migrationBuilder.CreateIndex(
                name: "IX_bills_StatusId",
                table: "bills",
                column: "StatusId");

            migrationBuilder.CreateIndex(
                name: "IX_BillItems_CategoryId",
                table: "BillItems",
                column: "CategoryId");

            migrationBuilder.AddForeignKey(
                name: "FK_BillItems_Categorie_CategoryId",
                table: "BillItems",
                column: "CategoryId",
                principalTable: "Categorie",
                principalColumn: "CategorieId");

            migrationBuilder.AddForeignKey(
                name: "FK_bills_Categorie_CategoryId",
                table: "bills",
                column: "CategoryId",
                principalTable: "Categorie",
                principalColumn: "CategorieId");

            migrationBuilder.AddForeignKey(
                name: "FK_bills_PaymentMethod_PaymentMethodId",
                table: "bills",
                column: "PaymentMethodId",
                principalTable: "PaymentMethod",
                principalColumn: "PaymentId");

            migrationBuilder.AddForeignKey(
                name: "FK_bills_PaymentStatus_StatusId",
                table: "bills",
                column: "StatusId",
                principalTable: "PaymentStatus",
                principalColumn: "StatusId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_BillItems_Categorie_CategoryId",
                table: "BillItems");

            migrationBuilder.DropForeignKey(
                name: "FK_bills_Categorie_CategoryId",
                table: "bills");

            migrationBuilder.DropForeignKey(
                name: "FK_bills_PaymentMethod_PaymentMethodId",
                table: "bills");

            migrationBuilder.DropForeignKey(
                name: "FK_bills_PaymentStatus_StatusId",
                table: "bills");

            migrationBuilder.DropTable(
                name: "Categorie");

            migrationBuilder.DropTable(
                name: "PaymentMethod");

            migrationBuilder.DropTable(
                name: "PaymentStatus");

            migrationBuilder.DropIndex(
                name: "IX_bills_CategoryId",
                table: "bills");

            migrationBuilder.DropIndex(
                name: "IX_bills_PaymentMethodId",
                table: "bills");

            migrationBuilder.DropIndex(
                name: "IX_bills_StatusId",
                table: "bills");

            migrationBuilder.DropIndex(
                name: "IX_BillItems_CategoryId",
                table: "BillItems");

            migrationBuilder.DropColumn(
                name: "CategoryId",
                table: "bills");

            migrationBuilder.DropColumn(
                name: "PaymentMethodId",
                table: "bills");

            migrationBuilder.DropColumn(
                name: "StatusId",
                table: "bills");

            migrationBuilder.DropColumn(
                name: "CategoryId",
                table: "BillItems");

            migrationBuilder.AddColumn<string>(
                name: "Category",
                table: "bills",
                type: "TEXT",
                nullable: true);

            migrationBuilder.AddColumn<string>(
                name: "PaymentMethod",
                table: "bills",
                type: "TEXT",
                nullable: true);

            migrationBuilder.AddColumn<string>(
                name: "Status",
                table: "bills",
                type: "TEXT",
                nullable: true,
                defaultValue: "Paid");

            migrationBuilder.AddColumn<string>(
                name: "Category",
                table: "BillItems",
                type: "TEXT",
                nullable: true);
        }
    }
}
