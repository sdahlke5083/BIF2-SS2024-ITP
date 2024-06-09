using Geld_Guardian.Pages.Data.Models;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;

namespace Geld_Guardian.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {

        public DbSet<Bill> Bills { get; set; }
        public DbSet<BillItem> BillItems { get; set; }
        public DbSet<Categorie> Categorie { get; set; }
        public DbSet<PaymentMethod> PaymentMethod { get; set; }

        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);



            // Seed data
            modelBuilder.Entity<Categorie>().HasData(
                new Categorie { CategorieId = 1, Name = "Groceries" },
                new Categorie { CategorieId = 2, Name = "Utilities" },
                new Categorie { CategorieId = 3, Name = "Rent" },
                new Categorie { CategorieId = 4, Name = "Transportation" },
                new Categorie { CategorieId = 5, Name = "Health" },
                new Categorie { CategorieId = 6, Name = "Entertainment" },
                new Categorie { CategorieId = 7, Name = "Education" },
                new Categorie { CategorieId = 8, Name = "Other" }
            );

            modelBuilder.Entity<PaymentMethod>().HasData(
                new PaymentMethod { PaymentId = 1, Name = "Cash" },
                new PaymentMethod { PaymentId = 2, Name = "Credit Card" },
                new PaymentMethod { PaymentId = 3, Name = "Debit Card" },
                new PaymentMethod { PaymentId = 4, Name = "Bank Transfer" },
                new PaymentMethod { PaymentId = 5, Name = "PayPal" },
                new PaymentMethod { PaymentId = 6, Name = "Other" }
            );

            modelBuilder.Entity<PaymentStatus>().HasData(
                new PaymentStatus { StatusId = 1, Name = "Pending" },
                new PaymentStatus { StatusId = 2, Name = "Paid" },
                new PaymentStatus { StatusId = 3, Name = "Overdue" }
            );

            // Setting default value and computed column
            modelBuilder.Entity<Bill>()
                .Property(b => b.StatusId)
                .HasDefaultValue(1);

            modelBuilder.Entity<Bill>()
                .Property(b => b.CategoryId)
                .HasDefaultValue(8);

            modelBuilder.Entity<Bill>()
                .Property(b => b.PaymentMethodId)
                .HasDefaultValue(1);

            modelBuilder.Entity<Bill>()
                .HasOne(b => b.User);

            modelBuilder.Entity<Bill>()
                .HasOne(b => b.PaymentMethod);

            modelBuilder.Entity<Bill>()
                .HasOne(b => b.Category);

            modelBuilder.Entity<Bill>()
                .HasOne(b => b.Status);

            // Configure BillItem with explicit foreign key to Bill
            modelBuilder.Entity<BillItem>()
                .HasOne(bi => bi.Bill) // Indicates that each BillItem has one Bill
                .WithMany(b => b.BillItems) // Indicates that a Bill can have many BillItems
                .HasForeignKey(bi => bi.BillId) // Explicitly sets BillId as the foreign key
                .OnDelete(DeleteBehavior.Cascade); // Deletes all BillItems when a Bill is deleted

            modelBuilder.Entity<BillItem>()
                .HasOne(bi => bi.Category);

            modelBuilder.Entity<BillItem>()
                .Property(bi => bi.CategoryId)
                .HasDefaultValue(8);


        }

    }
}
